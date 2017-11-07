package zadaci;

public class Stack {
	
	private String file;
	private int line;
	private String code;
	
	public Stack() {
		super();
	}
	public Stack(String file, int line, String code) {
		super();
		this.file = file;
		this.line = line;
		this.code = code;
	}
	public String getFile() {
		return file;
	}
	public void setFile(String file) {
		this.file = file;
	}
	public int getLine() {
		return line;
	}
	public void setLine(int line) {
		this.line = line;
	}
	public String getCode() {
		return code;
	}
	public void setCode(String code) {
		this.code = code;
	}
	@Override
	public String toString() {
		return "Stack [file=" + file + ", line=" + line + ", code=" + code
				+ "]";
	}
	
	

}
