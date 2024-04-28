use std::io::Write;

use gilrs::{Axis, Button, Event, EventType, Gilrs};
use serialport::{SerialPort, SerialPortBuilder};

fn main() {

    let mut gilrs = Gilrs::new().unwrap();

    // Iterate over all connected gamepads
    for (_id, gamepad) in gilrs.gamepads() {
        println!("{} is {:?}", gamepad.name(), gamepad.power_info());
    }

    let mut active_gamepad = None;

    let mut sp = serialport::new("/dev/tty.usbserial-B0004H6P", 57600).open_native().expect("Serial Port");

    loop {
        // Examine new events
        while let Some(Event { id, event, time }) = gilrs.next_event() {
            println!("{:?} New event from {}: {:?}", time, id, event);
            active_gamepad = Some(id);
            match event {
                EventType::AxisChanged(Axis::LeftStickY, pos, _) => {
                    println!("Throttle is {pos}");
                    sp.write(&[12, 0, (1.0+(19.0*(pos+1.0)/2.0)) as u8]).expect("failed to write");
                },
                EventType::AxisChanged(Axis::LeftStickX, pos, _) => {
                    println!("FlaperonRoll is {pos}");
                    sp.write(&[12, 1, (1.0+(19.0*(pos+1.0)/2.0)) as u8]).expect("failed to write");
                    sp.write(&[12, 2, (20.0-(19.0*(pos+1.0)/2.0)) as u8]).expect("failed to write");
                },
                EventType::AxisChanged(Axis::RightStickY, pos, _) => {
                    println!("FlaperonTrim is {pos}");
                },
                EventType::AxisChanged(Axis::RightStickX, pos, _) => {
                    println!("Rudder is {pos}");
                    sp.write(&[12, 3, (1.0+(19.0*(pos+1.0)/2.0)) as u8]).expect("failed to write");
                },
                _ => ()
            }
        }

    }
}
