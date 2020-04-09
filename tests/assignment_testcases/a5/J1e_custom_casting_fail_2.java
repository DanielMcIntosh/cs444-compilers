public class J1e_custom_casting_fail_2 {
	public J1e_custom_casting_fail_2() {}
	
	public static int test() {
        Object a = new Object[1];
        Integer[] b = (Integer[]) a;
        
		return 123;
	}
}
