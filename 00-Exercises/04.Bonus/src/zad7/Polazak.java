package zad7;

public class Polazak implements Comparable<Polazak>{
	
	private String id_putnika;
	private String ime_prezime_putnika;
	private String id_polaska;
	private String datum_polaska;
	private String vreme_polaska;
	private String mesto_polaska;
	private String mesto_dolaska;
	private String tip_karte; // char (d - dnevna, n - nedeljna, m - mesecna, g - godisnja)
	private String cena_karte;
	
	public Polazak() {
		super();
	}

	

	public Polazak(String id_putnika, String ime_prezime_putnika, String id_polaska, String datum_polaska,
			String vreme_polaska, String mesto_polaska, String mesto_dolaska, String tip_karte, String cena_karte) {
		super();
		this.id_putnika = id_putnika;
		this.ime_prezime_putnika = ime_prezime_putnika;
		this.id_polaska = id_polaska;
		this.datum_polaska = datum_polaska;
		this.vreme_polaska = vreme_polaska;
		this.mesto_polaska = mesto_polaska;
		this.mesto_dolaska = mesto_dolaska;
		this.tip_karte = tip_karte;
		this.cena_karte = cena_karte;
	}



	public String getId_putnika() {
		return id_putnika;
	}



	public void setId_putnika(String id_putnika) {
		this.id_putnika = id_putnika;
	}



	public String getIme_prezime_putnika() {
		return ime_prezime_putnika;
	}



	public void setIme_prezime_putnika(String ime_prezime_putnika) {
		this.ime_prezime_putnika = ime_prezime_putnika;
	}



	public String getId_polaska() {
		return id_polaska;
	}



	public void setId_polaska(String id_polaska) {
		this.id_polaska = id_polaska;
	}



	public String getDatum_polaska() {
		return datum_polaska;
	}



	public void setDatum_polaska(String datum_polaska) {
		this.datum_polaska = datum_polaska;
	}



	public String getVreme_polaska() {
		return vreme_polaska;
	}



	public void setVreme_polaska(String vreme_polaska) {
		this.vreme_polaska = vreme_polaska;
	}



	public String getMesto_polaska() {
		return mesto_polaska;
	}



	public void setMesto_polaska(String mesto_polaska) {
		this.mesto_polaska = mesto_polaska;
	}



	public String getMesto_dolaska() {
		return mesto_dolaska;
	}



	public void setMesto_dolaska(String mesto_dolaska) {
		this.mesto_dolaska = mesto_dolaska;
	}



	public String getTip_karte() {
		return tip_karte;
	}



	public void setTip_karte(String tip_karte) {
		this.tip_karte = tip_karte;
	}



	public String getCena_karte() {
		return cena_karte;
	}



	public void setCena_karte(String cena_karte) {
		this.cena_karte = cena_karte;
	}



	@Override
	public String toString() {
		return "Polazak [id_putnika=" + id_putnika + ", ime_prezime_putnika=" + ime_prezime_putnika + ", id_polaska="
				+ id_polaska + ", datum_polaska=" + datum_polaska + ", vreme_polaska=" + vreme_polaska
				+ ", mesto_polaska=" + mesto_polaska + ", mesto_dolaska=" + mesto_dolaska + ", tip_karte=" + tip_karte
				+ ", cena_karte=" + cena_karte + "]";
	}



	@Override
	public int compareTo(Polazak p) {
		return this.ime_prezime_putnika.compareTo(p.getIme_prezime_putnika());
	}



	
	
	
}
