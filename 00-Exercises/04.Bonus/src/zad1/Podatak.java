package zad1;

public class Podatak implements Comparable<Podatak>{
	
	private String sifraRelacije;
	private String mestoPolaska;
	private String mestoDolaska;
	private String datumPolaska;
	private String vremePolaska;
	private String planiranoVremeDolaska;
	private String peronPolaska;
	private String cenaKarte;
	private String brProdKarata;
	private String brRelacija;

	public Podatak() {
		super();
	}

	public Podatak(String sifraRelacije, String mestoPolaska, String mestoDolaska, String datumPolaska,
			String vremePolaska, String planiranoVremeDolaska, String peronPolaska, String cenaKarte, String brProdKarata,
			String brRelacija) {
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

	public String getCenaKarte() {
		return cenaKarte;
	}

	public void setCenaKarte(String cenaKarte) {
		this.cenaKarte = cenaKarte;
	}

	public String getBrProdKarata() {
		return brProdKarata;
	}

	public void setBrProdKarata(String brProdKarata) {
		this.brProdKarata = brProdKarata;
	}

	public String getBrRelacija() {
		return brRelacija;
	}

	public void setBrRelacija(String brRelacija) {
		this.brRelacija = brRelacija;
	}

	@Override
	public String toString() {
		return "Podatak [sifraRelacije=" + sifraRelacije + ", mestoPolaska=" + mestoPolaska + ", mestoDolaska="
				+ mestoDolaska + ", datumPolaska=" + datumPolaska + ", vremePolaska=" + vremePolaska
				+ ", planiranoVremeDolaska=" + planiranoVremeDolaska + ", peronPolaska=" + peronPolaska + ", cenaKarte="
				+ cenaKarte + ", brProdKarata=" + brProdKarata + ", brRelacija=" + brRelacija + "]";
	}
	
	@Override
	public int compareTo(Podatak p) {
		
		int status = 0;
		
		if(p.getSifraRelacije() != null)
			status += this.sifraRelacije.compareTo(p.getSifraRelacije());
		
		if(p.getMestoPolaska() != null)
			status += this.mestoPolaska.compareTo(p.getMestoPolaska());
		
		if(p.getMestoDolaska() != null)
			status += this.mestoDolaska.compareTo(p.getMestoDolaska());
		
		if(p.getDatumPolaska() != null)
			status += this.datumPolaska.compareTo(p.getDatumPolaska());
		
		if(p.getVremePolaska() != null)
			status += this.vremePolaska.compareTo(p.getVremePolaska());
		
		if(p.getPlaniranoVremeDolaska() != null)
			status += this.planiranoVremeDolaska.compareTo(p.getPlaniranoVremeDolaska());
		
		if(p.getPeronPolaska() != null)
			status += this.peronPolaska.compareTo(p.getPeronPolaska());
		
		if(p.getCenaKarte() != null) {
			if(Integer.parseInt(this.cenaKarte) == Integer.parseInt(p.getCenaKarte())){
				status += 0; // u sustini nepotrebno 
			}else {
				status += 99;
			}
		}
		
		if(p.getBrProdKarata() != null) {
			if(Integer.parseInt(this.brProdKarata) == Integer.parseInt(p.getBrProdKarata())){
				status += 0; // u sustini nepotrebno 
			}else {
				status += 99;
			}
		}
		
		if(p.getBrRelacija() != null) {
			if(Integer.parseInt(this.brRelacija) == Integer.parseInt(p.getBrRelacija())){
				status += 0; // u sustini nepotrebno 
			}else {
				status += 99;
			}
		}
		
		
		return status;
		

}
	
	
	
	
}
