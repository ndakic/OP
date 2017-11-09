package zad1;

public class Relacija {
	
	
	private String sifraRelacije;
	private String mestoPolaska;
	private String mestoDolaska;
	
	public Relacija() {
		super();
	}

	public Relacija(String sifraRelacije, String mestoPolaska, String mestoDolaska) {
		super();
		this.sifraRelacije = sifraRelacije;
		this.mestoPolaska = mestoPolaska;
		this.mestoDolaska = mestoDolaska;
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

	@Override
	public String toString() {
		return "Relacija [sifraRelacije=" + sifraRelacije + ", mestoPolaska=" + mestoPolaska + ", mestoDolaska="
				+ mestoDolaska + "]";
	}
	
	

}
