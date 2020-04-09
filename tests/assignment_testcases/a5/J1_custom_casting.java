import java.io.*;

public class J1_custom_casting {
	public J1_custom_casting() {}
	
	public static int test() {
        Object a = new int[1];
		int[] b = (int[]) a;

        Object c = new Integer[1];
        Object[] d = (Object[]) c;

        Integer[] e = (Integer[]) new Integer[1];

        OutputStream[] f = (OutputStream[]) new PrintStream[1];

        Object g = new PrintStream[1];
        OutputStream[] h = (OutputStream[]) g;

		return 123;
	}
}
