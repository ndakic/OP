package zad1;

public class Podatak {
	
	private String sifraRelacije;
	private String mestoPolaska;
	private String mestoDolaska;
	private String datumPolaska;
	private String vremePolaska;
	private String planiranoVremeDolaska;
	private String peronPolaska;
	private int cenaKarte;
	private int brProdKarata;
	
	private int brRelacija;

	public Podatak() {
		super();
	}

	public Podatak(String sifraRelacije, String mestoPolaska, String mestoDolaska, String datumPolaska,
			String vremePolaska, String planiranoVremeDolaska, String peronPolaska, int cenaKarte, int brProdKarata,
			int brRelacija) {
		super();
		this.sifraRelacije = sifraRelacije;
		this.mestoPolaska = mestoPolaska;
		this.mestoDolaska = mestoDolaska;
		this.datumPolaska = datumPolaska;
		this.vremePolaska = vremePolaska;
		this.planiranoVremeDolaska = planiranoVremeDolaska;
		this.peronPolaska = peronPolaska;
		this.cenaKarte = cenaKarte;
		this.brProdKarata = brProdKarata;
		this.brRelacija = brRelacija;
	}

	public String getSifraRelacije() {
		return sifraRelacije;
	}

	public void setSifraRelacije(String sifraRelacije) {
		this.sifraRelacije = sifraRelacije;
	}

	public String getMestoPolaska() {
		return mestoPolaska;
	}

	public void setMestoPolaska(String mestoPolaska) {
		this.mestoPolaska = mestoPolaska;
	}

	public String getMestoDolaska() {
		return mestoDolaska;
	}

	public void setMestoDolaska(String mestoDolaska) {
		this.mestoDolaska = mestoDolaska;
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

	public int getBrRelacija() {
		return brRelacija;
	}

	public void setBrRelacija(int brRelacija) {
		this.brRelacija = brRelacija;
	}

	@Override
	public String toString() {
		return "Podatak [sifraRelacije=" + sifraRelacije + ", mestoPolaska=" + mestoPolaska + ", mestoDolaska="
				+ mestoDolaska + ", datumPolaska=" + datumPolaska + ", vremePolaska=" + vremePolaska
				+ ", planiranoVremeDolaska=" + planiranoVremeDolaska + ", peronPolaska=" + peronPolaska + ", cenaKarte="
				+ cenaKarte + ", brProdKarata=" + brProdKarata + ", brRelacija=" + brRelacija + "]";
	}
	
	
	
	
}
