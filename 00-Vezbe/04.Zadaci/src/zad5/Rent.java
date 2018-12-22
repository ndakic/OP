package zad5;

public class Rent implements Comparable<Rent>{
	
	private String sifraIzn;
	private String mestoIzn;
	private String datumIzn;
	private String datumVrac;
	private String predjenoKm;
	private String cenaIznNaDan;
	private String brojIznDana;
	private Osoba osoba;
	
	public Rent() {
		super();
	}
	public Rent(String sifraIzn, String mestoIzn, String datumIzn, String datumVrac, String predjenoKm,
			String cenaIznNaDan, String brojIznDana, Osoba osoba) {
		super();
		this.sifraIzn = sifraIzn;
		this.mestoIzn = mestoIzn;
		this.datumIzn = datumIzn;
		this.datumVrac = datumVrac;
		this.predjenoKm = predjenoKm;
		this.cenaIznNaDan = cenaIznNaDan;
		this.brojIznDana = brojIznDana;
		this.osoba = osoba;
	}
	public String getSifraIzn() {
		return sifraIzn;
	}
	public void setSifraIzn(String sifraIzn) {
		this.sifraIzn = sifraIzn;
	}
	public String getMestoIzn() {
		return mestoIzn;
	}
	public void setMestoIzn(String mestoIzn) {
		this.mestoIzn = mestoIzn;
	}
	public String getDatumIzn() {
		return datumIzn;
	}
	public void setDatumIzn(String datumIzn) {
		this.datumIzn = datumIzn;
	}
	public String getDatumVrac() {
		return datumVrac;
	}
	public void setDatumVrac(String datumVrac) {
		this.datumVrac = datumVrac;
	}
	public String getPredjenoKm() {
		return predjenoKm;
	}
	public void setPredjenoKm(String predjenoKm) {
		this.predjenoKm = predjenoKm;
	}
	public String getCenaIznNaDan() {
		return cenaIznNaDan;
	}
	public void setCenaIznNaDan(String cenaIznNaDan) {
		this.cenaIznNaDan = cenaIznNaDan;
	}
	public String getBrojIznDana() {
		return brojIznDana;
	}
	public void setBrojIznDana(String brojIznDana) {
		this.brojIznDana = brojIznDana;
	}
	public Osoba getOsoba() {
		return osoba;
	}
	public void setOsoba(Osoba osoba) {
		this.osoba = osoba;
	}
	@Override
	public String toString() {
		return "Rent [sifraIzn=" + sifraIzn + ", mestoIzn=" + mestoIzn + ", datumIzn=" + datumIzn + ", datumVrac="
				+ datumVrac + ", predjenoKm=" + predjenoKm + ", cenaIznNaDan=" + cenaIznNaDan + ", brojIznDana="
				+ brojIznDana + ", osoba=" + osoba + "]";
	}
	
	@Override
	public int compareTo(Rent o) {
		
		return Integer.parseInt(o.getPredjenoKm()) - Integer.parseInt(this.predjenoKm)  ;
		
	}
	
	
	public int compareObjectsToByOsoba(Rent o) {
		
		return this.osoba.getMaticniBroj().compareTo(o.getOsoba().getMaticniBroj());
		
		
	}
	
	
}
