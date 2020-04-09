public class J1e_custom_casting_fail_3 {
	public J1e_custom_casting_fail_3() {}
	
	public static int test() {
        Integer[] a = (Integer[]) new Object[1];

		return 123;
	}
}
