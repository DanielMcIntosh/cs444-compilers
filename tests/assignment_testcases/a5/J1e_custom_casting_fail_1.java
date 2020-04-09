public class J1e_custom_casting_fail_1 {
	public J1e_custom_casting_fail_1() {}
	
	public static int test() {
        Object a = new int[1];
        Integer[] b = (Integer[]) a;

		return 123;
	}
}
