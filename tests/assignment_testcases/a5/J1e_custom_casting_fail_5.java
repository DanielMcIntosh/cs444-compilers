public class J1e_custom_casting_fail_5 {
	public J1e_custom_casting_fail_5() {}
	
	public static int test() {
        Integer a = (Integer) new Object();

		return 123;
	}
}
