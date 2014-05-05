import java.awt.AWTException;
import java.util.Random;


public class Main {

	public static void main(String[] args) {
		MouseControl test = null;
		try {
			test = new MouseControl();
		} 
		catch (AWTException e) {
			e.printStackTrace();
		}
		for (int i=0; i<500; i++) {
			int low = -800;
			int high = 800;
			Random rng = new Random();
			int x_accel = rng.nextInt(high-low)+low;
			int y_accel = rng.nextInt(high-low)+low;
			test.moveMouseDX(x_accel, y_accel);
		}
	}	
}
