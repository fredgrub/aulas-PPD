
class UsaLong {
  long num = -100;
  public void incrementaLong() {
    while (true) {
      num++;
      if (num > 99)
        num = -100;
    }
  }
  public long verificaLong() {
    long temp = 0;
    while (temp >= -100 && temp <= 100)
      temp = num;
    return temp;
  }
}

class Objeto1 implements Runnable {
  UsaLong my;
  public Objeto1(UsaLong l) { my = l; }
  public void run() { my.incrementaLong(); }
}

class Objeto2 implements Runnable {
  UsaLong my;
  public Objeto2(UsaLong l) { my = l; }
  public void run() {
    System.out.println(my.verificaLong());
    System.exit(0);
  }
}
public class NonAtomicLong {
  public static void main(String a[]) {
    System.out.println("Comecei...");
    UsaLong l = new UsaLong();
    Objeto1 obj1 = new Objeto1(l);
    Objeto2 obj2 = new Objeto2(l);
    Thread t1 = new Thread(obj1);
    Thread t2 = new Thread(obj2);
    t1.start();
    t2.start();
  }
}