package zad6Kol1;

public class Projekcija {
	
	private String sifraSale;
	private String nazivSale;
	private String datum;
	private String vreme;
	private String trajanje; // celobrojna vrednost u minutima
	private String film;
	
	public Projekcija() {
		super();
	}
	
	public Projekcija(String sifraSale, String nazivSale, String datum, String vreme, String trajanje, String film) {
		super();
		this.sifraSale = sifraSale;
		this.nazivSale = nazivSale;
		this.datum = datum;
		this.vreme = vreme;
		this.trajanje = trajanje;
		this.film = film;
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
	public String getDatum() {
		return datum;
	}
	public void setDatum(String datum) {
		this.datum = datum;
	}
	public String getVreme() {
		return vreme;
	}
	public void setVreme(String vreme) {
		this.vreme = vreme;
	}
	public String getTrajanje() {
		return trajanje;
	}
	public void setTrajanje(String trajanje) {
		this.trajanje = trajanje;
	}
	public String getFilm() {
		return film;
	}
	public void setFilm(String film) {
		this.film = film;
	}
	
	@Override
	public String toString() {
		return "Projekcija [sifraSale=" + sifraSale + ", nazivSale=" + nazivSale + ", datum=" + datum + ", vreme="
				+ vreme + ", trajanje=" + trajanje + ", film=" + film + "]";
	}


}
