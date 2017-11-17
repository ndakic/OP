package zad7;

public class Izvestaj implements Comparable<Izvestaj> {
	
	private String idPutnika;
	private String imePrezimePutnika;
	private String brKarata;
	private String najVreme;
	
	
	public Izvestaj() {
		super();
	}

	public Izvestaj(String idPutnika, String imePrezimePutnika, String brKarata, String najVreme) {
		super();
		this.idPutnika = idPutnika;
		this.imePrezimePutnika = imePrezimePutnika;
		this.brKarata = brKarata;
		this.najVreme = najVreme;
	}

	public String getIdPutnika() {
		return idPutnika;
	}

	public void setIdPutnika(String idPutnika) {
		this.idPutnika = idPutnika;
	}

	public String getImePrezimePutnika() {
		return imePrezimePutnika;
	}

	public void setImePrezimePutnika(String imePrezimePutnika) {
		this.imePrezimePutnika = imePrezimePutnika;
	}

	public String getBrKarata() {
		return brKarata;
	}

	public void setBrKarata(String brKarata) {
		this.brKarata = brKarata;
	}

	public String getNajVreme() {
		return najVreme;
	}

	public void setNajVreme(String najVreme) {
		this.najVreme = najVreme;
	}

	@Override
	public String toString() {
		return "Izvestaj [idPutnika=" + idPutnika + ", imePrezimePutnika=" + imePrezimePutnika + ", brKarata="
				+ brKarata + ", najVreme=" + najVreme + "]";
	}

	@Override
	public int compareTo(Izvestaj izv) {
		
		return this.imePrezimePutnika.compareTo(izv.getImePrezimePutnika());
	}
	
	
}
