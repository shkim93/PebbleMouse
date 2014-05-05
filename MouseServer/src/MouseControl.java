import java.awt.AWTException;
import java.awt.Dimension;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.Robot;
import java.awt.Toolkit;

public class MouseControl {
	private static int x;
	private static int y;
	private static Robot robo;
	
	public MouseControl() throws AWTException {
		Point start = currentSpot();
		x = (int)start.getX();
		y = (int)start.getY();		
		robo = new Robot();
	}
	
	public static Point currentSpot() {
		return MouseInfo.getPointerInfo().getLocation();
	}
	
	public static void moveMouse(int x_accel, int y_accel) {
		Point now = currentSpot();
		x = (int)now.getX();
		y = (int)now.getY();
		int x2 = x + x_accel + 1;
		int y2 = y + y_accel + 1;

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		if (x2 > (int)screenSize.getWidth() || y2 > (int)screenSize.getHeight()) {
			x_accel = 0;
			y_accel = 0;
		}
		if (x2 < 0 || y2 < 0) {
			x_accel = 0;
			y_accel = 0;
		}
		
		robo.mouseMove(x+x_accel,y+y_accel);
		robo.delay(10);
	}
	
	public static int speedControl(int pikachu) {
		if (pikachu > 700) {
			return 6;
		}
		if (pikachu < -700) {
			return -6;
		}
		if (pikachu > 500) {
			return 5;
		}
		if (pikachu < -500) {
			return -5;
		}
		if (pikachu > 350) {
			return 4;
		}
		if (pikachu < -350) {
			return -4;
		}
		if (pikachu > 250) {
			return 3;
		}
		if (pikachu < -250) {
			return -3;
		}
		if (pikachu > 200) {
			return 2;
		}
		if (pikachu < -200) {
			return -2;
		}
		if (pikachu > 150) {
			return 1;
		}
		if (pikachu < -150) {
			return -1;
		}
		return 0;
	}
	
	public void moveMouseDX(int x_xl, int y_xl) {
		moveMouse(speedControl(x_xl), speedControl(y_xl));
	}
	
	
}
