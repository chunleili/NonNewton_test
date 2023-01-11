from draw_base import DrawBase

def run_PowerLaw():
    model_name = "Casson"
    param_name = "yield_stress"
    param_val = [10.0* i for i in range(0, 10)]
    a = DrawBase(model_name, param_name, param_val, case_start=1, case_end=10)
    a.run()

if __name__ == '__main__':
    run_PowerLaw()