use std::env;
use std::ffi::c_double;
use std::process::exit;

unsafe extern "C" {
	pub fn Struve(x: c_double, v: c_double) -> c_double;
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

	let res = unsafe { Struve(x as c_double, v as c_double) };
	println!("Struve({}, {}) = {}", x, v, res);
}
