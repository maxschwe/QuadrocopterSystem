using DifferentialEquations, Plots

# 1. Return a Vector (use commas, not spaces)
f(t) = [sin(t), cos(t), sin(2t), cos(2t)]

trange = range(0, 10, length=100)

# 2. stack(f.(trange)) creates a 4x100 Matrix. 
# 3. Transpose it (') to get 100x4 (Time x Series).
data = stack(f.(trange))'

# 4. Plot (Note: Title must be a Row Vector/1x4 Matrix to apply to subplots)
plot(trange, data, 
     layout = 4, 
     title = ["V1" "V2" "V3" "V4"],
     legend = false)