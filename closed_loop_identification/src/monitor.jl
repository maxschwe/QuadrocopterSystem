using LibSerialPort
using DataFrames

portname = "COM4"
baudrate = 921600

# Updated headers: 15 columns (Time + 14 Data Fields)
headers = [
    :time_ms, 
    :roll_actual, :pitch_actual, :yaw_actual, 
    :roll_cmd, :pitch_cmd, :yaw_cmd, :throttle_cmd, 
    :throttle_1, :throttle_2, :throttle_3, :throttle_4, 
    :roll_modeled, :pitch_modeled, :yaw_modeled
]

# time_ms as Int64, all telemetry values as Float64
df = DataFrame([h => (h == :time_ms ? Int64[] : Float64[]) for h in headers])

LibSerialPort.open(portname, baudrate) do sp
    flush(sp)
    
    start_time = -1
    line_count = 0

    while isopen(sp)
        line = readline(sp)
        if startswith(line, '#')
            parts = split(lstrip(line, '#'), '\t', keepempty=false)
            
            if length(parts) == 15
                raw_t = parse(Int64, parts[1])
                
                if start_time == -1
                    start_time = raw_t
                    continue
                end
                
                relative_t = raw_t - start_time
                floats = parse.(Float64, parts[2:end])

                push!(df, [relative_t; floats])
                
                line_count += 1
                if line_count % 100 == 0
                    println("Relative Time: $(round(relative_t / 1000, digits=2))s | Roll: $(rad2deg(floats[1]))")
                end
            end
        else
            println("Received non-data line: ", line)
        end
    end
end
