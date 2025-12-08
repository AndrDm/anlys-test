use std::env;
use std::ffi::c_double;
use std::process::exit;

unsafe extern "C" {
	// C: void LV_Struve(double x, double v, double *Struve);
	pub fn LV_Struve(x: c_double, v: c_double, Struve: *mut c_double);
}

fn usage(prog: &str) -> ! {
	eprintln!("usage: {} <x> <v>", prog);
	eprintln!("Struve Tester");
	eprintln!("    x    real argument of the Struve function H_v(x)");
	eprintln!("    v    order (index) of the Struve function H_v(x)");
	exit(1);
}

fn main() {
	let args: Vec<String> = env::args().collect();
	if args.len() != 3 {
		usage(&args[0]);
	}

	let x: f64 = args[1].parse::<f64>().expect(
		"invalid x: expected a floating-point number (e.g., 1.23 or 1e-3)",
	);
	let v: f64 = args[2]
		.parse::<f64>()
		.expect("invalid v: expected a floating-point number (e.g., 0.5)");

	let mut res: c_double = 0.0;
	unsafe {
		// Call the C function: it writes into `res`
		LV_Struve(x as c_double, v as c_double, &mut res as *mut c_double);
	}

	println!("LV_Struve({}, {}) = {}", x, v, res as f64);
}
