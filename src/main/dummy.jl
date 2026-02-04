
# teval = 0:Ts:t_end


function controller(t, x)
    return -K*x
end

function dxdt(t, x, u; p=-0.8)
    return p*x
end

function closed_loop_sys(t, x; p=-0.8)
    u = controller(t, x)
    dxdt = dxdt(t, x, u; p=p)
    return dxdt
end

solver(closed_loop_sys, x0, tspan, runge_kutta)

# scipy.solve_ivp( )        # python