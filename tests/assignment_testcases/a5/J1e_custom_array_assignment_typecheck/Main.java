import pkg.*;

public class Main {
  public Main() {}
  public static int test() {
    Apple[] as = new Apple[1];
    Fruit[] fs = as;
    fs[0] = new Orange();
    Apple a = as[0];
    return 123;
  }
}
