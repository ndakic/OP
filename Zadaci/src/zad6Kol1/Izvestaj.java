package zad6Kol1;

public class Izvestaj implements Comparable<Izvestaj>{
	
	private String sifraSale;
	private String nazivSale;
	private String najkrace;
	private String najduze;
	private String prosecno;
	private String datum;
	
	public Izvestaj() {
		super();
	}

	public Izvestaj(String sifraSale, String nazivSale, String najkrace, String najduze, String prosecno,String datum) {
		super();
		this.sifraSale = sifraSale;
		this.nazivSale = nazivSale;
		this.najkrace = najkrace;
		this.najduze = najduze;
		this.prosecno = prosecno;
		this.datum = datum;
	}

	public String getSifraSale() {
		return sifraSale;
	}

	public void setSifraSale(String sifraSale) {
		this.sifraSale = sifraSale;
	}

	public String getNazivSale() {
		return nazivSale;
	}

	public void setNazivSale(String nazivSale) {
		this.nazivSale = nazivSale;
	}

	public String getNajkrace() {
		return najkrace;
	}

	public void setNajkrace(String najkrace) {
		this.najkrace = najkrace;
	}

	public String getNajduze() {
		return najduze;
	}

	public void setNajduze(String najduze) {
		this.najduze = najduze;
	}

	public String getProsecno() {
		return prosecno;
	}

	public void setProsecno(String prosecno) {
		this.prosecno = prosecno;
	}
	
	

	public String getDatum() {
		return datum;
	}

	public void setDatum(String datum) {
		this.datum = datum;
	}

	@Override
	public String toString() {
		return "Izvestaj [sifraSale=" + sifraSale + ", nazivSale=" + nazivSale + ", najkrace=" + najkrace + ", najduze="
				+ najduze + ", prosecno=" + prosecno + ", datum=" + datum + "]";
	}

	@Override
	public int compareTo(Izvestaj izvestaj) {
		return Integer.parseInt(this.sifraSale) - Integer.parseInt(izvestaj.getSifraSale());
	}

	
	
	


}
