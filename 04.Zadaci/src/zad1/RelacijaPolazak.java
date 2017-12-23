package zad1;

import java.util.List;

public class RelacijaPolazak {
	
	private List<Relacija> relacije;
	private List<Polazak> polasci;
	
	public RelacijaPolazak() {
		super();
	}

	public RelacijaPolazak(List<Relacija> relacije, List<Polazak> polasci) {
		super();
		this.relacije = relacije;
		this.polasci = polasci;
	}

	public List<Relacija> getRelacije() {
		return relacije;
	}

	public void setRelacije(List<Relacija> relacije) {
		this.relacije = relacije;
	}

	public List<Polazak> getPolasci() {
		return polasci;
	}

	public void setPolasci(List<Polazak> polasci) {
		this.polasci = polasci;
	}



}
