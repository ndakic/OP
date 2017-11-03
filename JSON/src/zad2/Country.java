package zad2;

public class Country implements Comparable<Country>{
	
	private String CountryName;
	private String CapitalName;
	private String CapitalLatitude;
	private String CapitalLongitude;
	private String CountryCode;
	private String ContinentName;
	
	
	public Country() {
		super();
	}

	public Country(String countryName, String capitalName, String capitalLatitude, String capitalLongitude,
			String countryCode, String continentName) {
		super();
		CountryName = countryName;
		CapitalName = capitalName;
		CapitalLatitude = capitalLatitude;
		CapitalLongitude = capitalLongitude;
		CountryCode = countryCode;
		ContinentName = continentName;
	}


	public String getCountryName() {
		return CountryName;
	}

	public void setCountryName(String countryName) {
		CountryName = countryName;
	}

	public String getCapitalName() {
		return CapitalName;
	}

	public void setCapitalName(String capitalName) {
		CapitalName = capitalName;
	}

	public String getCapitalLatitude() {
		return CapitalLatitude;
	}

	public void setCapitalLatitude(String capitalLatitude) {
		CapitalLatitude = capitalLatitude;
	}

	public String getCapitalLongitude() {
		return CapitalLongitude;
	}

	public void setCapitalLongitude(String capitalLongitude) {
		CapitalLongitude = capitalLongitude;
	}

	public String getCountryCode() {
		return CountryCode;
	}

	public void setCountryCode(String countryCode) {
		CountryCode = countryCode;
	}

	public String getContinentName() {
		return ContinentName;
	}

	public void setContinentName(String continentName) {
		ContinentName = continentName;
	}

	@Override
	public int compareTo(Country o) {
		return (this.ContinentName.compareTo(o.getContinentName()));
	}

	@Override
	public String toString() {
		return "Country [CountryName=" + CountryName + ", CapitalName=" + CapitalName + ", CapitalLatitude="
				+ CapitalLatitude + ", CapitalLongitude=" + CapitalLongitude + ", CountryCode=" + CountryCode
				+ ", ContinentName=" + ContinentName + "]";
	}
	
	
	
	

}


