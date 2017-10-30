package CSV.examples;

public class Country {


	private String countryName;
	private String capitalName;
	private String capitalLatitude;
	private String capitalLongitude;
	private String countryCode;
	private String continentName;
	
	public Country() {
		super();
	}

	public Country(String countryName, String capitalName, String capitalLatitude, String capitalLongitude,
			String countryCode, String continentName) {
		super();
		this.countryName = countryName;
		this.capitalName = capitalName;
		this.capitalLatitude = capitalLatitude;
		this.capitalLongitude = capitalLongitude;
		this.countryCode = countryCode;
		this.continentName = continentName;
	}

	public String getCountryName() {
		return countryName;
	}

	public void setCountryName(String countryName) {
		this.countryName = countryName;
	}

	public String getCapitalName() {
		return capitalName;
	}

	public void setCapitalName(String capitalName) {
		this.capitalName = capitalName;
	}

	public String getCapitalLatitude() {
		return capitalLatitude;
	}

	public void setCapitalLatitude(String capitalLatitude) {
		this.capitalLatitude = capitalLatitude;
	}

	public String getCapitalLongitude() {
		return capitalLongitude;
	}

	public void setCapitalLongitude(String capitalLongitude) {
		this.capitalLongitude = capitalLongitude;
	}

	public String getCountryCode() {
		return countryCode;
	}

	public void setCountryCode(String countryCode) {
		this.countryCode = countryCode;
	}

	public String getContinentName() {
		return continentName;
	}

	public void setContinentName(String continentName) {
		this.continentName = continentName;
	}

	@Override
	public String toString() {
		return "Country [countryName=" + countryName + ", capitalName=" + capitalName + ", capitalLatitude="
				+ capitalLatitude + ", capitalLongitude=" + capitalLongitude + ", countryCode=" + countryCode
				+ ", continentName=" + continentName + "]";
	}
	
	
}
