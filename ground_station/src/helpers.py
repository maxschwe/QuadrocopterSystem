def format_ms(ms):
    minutes, ms = divmod(ms, 60000)
    seconds, ms = divmod(ms, 1000)
    return f"{int(minutes):02}:{int(seconds):02}.{int(ms):03}"
