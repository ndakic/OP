package zad5;

public class SumaProsek {
	
	private String matBrOsobe;
	private String potrosenaSuma;
	private String prosekDana;
	
	public SumaProsek() {
		super();
	}

	public SumaProsek(String matBrOsobe, String potrosenaSuma, String prosekDana) {
		super();
		this.matBrOsobe = matBrOsobe;
		this.potrosenaSuma = potrosenaSuma;
		this.prosekDana = prosekDana;
	}

	public String getMatBrOsobe() {
		return matBrOsobe;
	}

	public void setMatBrOsobe(String matBrOsobe) {
		this.matBrOsobe = matBrOsobe;
	}

	public String getPotrosenaSuma() {
		return potrosenaSuma;
	}

	public void setPotrosenaSuma(String potrosenaXuma) {
		this.potrosenaSuma = potrosenaXuma;
	}

	public String getProsekDana() {
		return prosekDana;
	}

	public void setProsekDana(String prosekDana) {
		this.prosekDana = prosekDana;
	}

	@Override
	public String toString() {
		return "SumaProsek [matBrOsobe=" + matBrOsobe + ", potrosenaSuma=" + potrosenaSuma + ", prosekDana="
				+ prosekDana + "]";
	}
	
	

}
