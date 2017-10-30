package CSV.zad1;

public class Point implements Comparable<Point> {
	
	private String x;
	private String y;
	private String z;
	private String p;
	public Point() {
		super();
	}
	public Point(String x, String y, String z, String p) {
		super();
		this.x = x;
		this.y = y;
		this.z = z;
		this.p = p;
	}
	public String getX() {
		return x;
	}
	public void setX(String x) {
		this.x = x;
	}
	public String getY() {
		return y;
	}
	public void setY(String y) {
		this.y = y;
	}
	public String getZ() {
		return z;
	}
	public void setZ(String z) {
		this.z = z;
	}
	public String getP() {
		return p;
	}
	public void setP(String p) {
		this.p = p;
	}
	@Override
	public String toString() {
		return "Point [x=" + x + ", y=" + y + ", z=" + z + ", p=" + p + "]";
	}
	
	@Override
	public int compareTo(Point point) {
		 return (Integer.parseInt(this.p)) - Integer.parseInt(point.p);
		//return Integer.parseInt(point.p) - (Integer.parseInt(this.p));
	}
	

}
