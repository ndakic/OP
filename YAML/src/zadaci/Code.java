package zadaci;

public class Code {
	
	private String x;
	private String foo;
	

	public Code() {
		super();
	}
	public Code(String x, String foo) {
		super();
		this.x = x;
		this.foo = foo;
	}
	public String getX() {
		return x;
	}
	public void setX(String x) {
		this.x = x;
	}
	public String getFoo() {
		return foo;
	}
	public void setFoo(String foo) {
		this.foo = foo;
	}
	@Override
	public String toString() {
		return "Code [x=" + x + ", foo=" + foo + "]";
	}
	
	

}
