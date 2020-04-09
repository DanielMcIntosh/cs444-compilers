public class J1e_custom_casting_fail_4 {
	public J1e_custom_casting_fail_4() {}
	
	public static int test() {
        Object a = new char[1];
        int[] b = (int[]) a;

		return 123;
	}
}
