package zad1;

public class Polazak {
	
	private String sifraRelacije;
	private String datumPolaska;
	private String vremePolaska;
	private String planiranoVremeDolaska;
	private String peronPolaska;
	private int cenaKarte;
	private int brProdKarata;
	
	public Polazak() {
		super();
	}

	public Polazak(String sifraRelacije, String datumPolaska, String vremePolaska, String planiranoVremeDolaska,
			String peronPolaska, int cenaKarte, int brProdKarata) {
		super();
		this.sifraRelacije = sifraRelacije;
		this.datumPolaska = datumPolaska;
		this.vremePolaska = vremePolaska;
		this.planiranoVremeDolaska = planiranoVremeDolaska;
		this.peronPolaska = peronPolaska;
		this.cenaKarte = cenaKarte;
		this.brProdKarata = brProdKarata;
	}

	public String getSifraRelacije() {
		return sifraRelacije;
	}

	public void setSifraRelacije(String sifraRelacije) {
		this.sifraRelacije = sifraRelacije;
	}

	public String getDatumPolaska() {
		return datumPolaska;
	}

	public void setDatumPolaska(String datumPolaska) {
		this.datumPolaska = datumPolaska;
	}

	public String getVremePolaska() {
		return vremePolaska;
	}

	public void setVremePolaska(String vremePolaska) {
		this.vremePolaska = vremePolaska;
	}

	public String getPlaniranoVremeDolaska() {
		return planiranoVremeDolaska;
	}

	public void setPlaniranoVremeDolaska(String planiranoVremeDolaska) {
		this.planiranoVremeDolaska = planiranoVremeDolaska;
	}

	public String getPeronPolaska() {
		return peronPolaska;
	}

	public void setPeronPolaska(String peronPolaska) {
		this.peronPolaska = peronPolaska;
	}

	public int getCenaKarte() {
		return cenaKarte;
	}

	public void setCenaKarte(int cenaKarte) {
		this.cenaKarte = cenaKarte;
	}

	public int getBrProdKarata() {
		return brProdKarata;
	}

	public void setBrProdKarata(int brProdKarata) {
		this.brProdKarata = brProdKarata;
	}

	@Override
	public String toString() {
		return "Relacija [sifraRelacije=" + sifraRelacije + ", datumPolaska=" + datumPolaska + ", vremePolaska="
				+ vremePolaska + ", planiranoVremeDolaska=" + planiranoVremeDolaska + ", peronPolaska=" + peronPolaska
				+ ", cenaKarte=" + cenaKarte + ", brProdKarata=" + brProdKarata + "]";
	}
	
	

}
