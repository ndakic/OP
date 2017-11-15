package zad5;

public class Osoba {

	private String ime;
	private String prezime;
	private String maticniBroj;
	
	public Osoba() {
		super();
	}

	public Osoba(String ime, String prezime, String maticniBroj) {
		super();
		this.ime = ime;
		this.prezime = prezime;
		this.maticniBroj = maticniBroj;
	}

	public String getIme() {
		return ime;
	}

	public void setIme(String ime) {
		this.ime = ime;
	}

	public String getPrezime() {
		return prezime;
	}

	public void setPrezime(String prezime) {
		this.prezime = prezime;
	}

	public String getMaticniBroj() {
		return maticniBroj;
	}

	public void setMaticniBroj(String maticniBroj) {
		this.maticniBroj = maticniBroj;
	}

	@Override
	public String toString() {
		return "Osoba [ime=" + ime + ", prezime=" + prezime + ", maticniBroj=" + maticniBroj + "]";
	}
	
	
	
}
