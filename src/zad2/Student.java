package zad2;

public class Student {

	private String index;
	private String ime;
	private String predmet;
	private String ocena;
	
	
	public Student() {
		super();
	}

	public Student(String index, String ime, String predmet, String ocena) {
		super();
		this.index = index;
		this.ime = ime;
		this.predmet = predmet;
		this.ocena = ocena;
	}

	public String getIndex() {
		return index;
	}

	public void setIndex(String index) {
		this.index = index;
	}

	public String getIme() {
		return ime;
	}

	public void setIme(String ime) {
		this.ime = ime;
	}

	public String getPredmet() {
		return predmet;
	}

	public void setPredmet(String predmet) {
		this.predmet = predmet;
	}

	public String getOcena() {
		return ocena;
	}

	public void setOcena(String ocena) {
		this.ocena = ocena;
	}

	@Override
	public String toString() {
		return "Student [index=" + index + ", ime=" + ime + ", predmet=" + predmet + ", ocena=" + ocena + "]";
	}
	
}
