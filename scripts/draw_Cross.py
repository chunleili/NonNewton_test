from draw_base import DrawBase

def run_Cross():
    model_name = "Cross"
    param_name = "power_index"
    param_val = [0.3 + 0.1* i for  i in range(0, 10)]
    a = DrawBase(model_name, param_name, param_val)
    a.run()

if __name__ == '__main__':
    run_Cross()