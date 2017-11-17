package zad7;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import au.com.bytecode.opencsv.CSVReader;
import au.com.bytecode.opencsv.CSVWriter;
import au.com.bytecode.opencsv.bean.BeanToCsv;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;
import au.com.bytecode.opencsv.bean.CsvToBean;

public class AutobuskaStanica {
	
	public static List<Polazak> polasci = null;

	public static void main(String[] args) throws IOException {
		
		upisiPolaskeCSV(createDate(), "polasci");
		
		polasci = ucitajPolaske("polasci");
		
		Collections.sort(polasci);	
		
		List<Izvestaj> izvestajJSON = new ArrayList<>();
		
		for(Polazak polazak: polasci) {
				
			if(!checkIzvestaj(izvestajJSON, polazak)) {
				
				int brKarata = brRazKarata(polazak);
				
				String vreme = najPolaska(polazak);
							
				Izvestaj izvestaj = new Izvestaj(polazak.getId_putnika(), polazak.getIme_prezime_putnika(), Integer.toString(brKarata), vreme );
				
				izvestajJSON.add(izvestaj);
			}
			
		}
		
		Collections.sort(izvestajJSON);
		
		sacuvajIzvestaj(izvestajJSON, "izvestaj");

	}
	
	public static String najPolaska(Polazak polazak) {
					
		HashMap<String, Integer> mapa = new HashMap<>();
		
		for(Polazak pol: polasci) {
			
			if(pol.getId_putnika().equalsIgnoreCase(polazak.getId_putnika())) {
				
				int br = brIstogVremena(pol.getId_putnika(), pol.getVreme_polaska());
				
				mapa.put(pol.getVreme_polaska(), br);
			}
			
		}
		
		String vreme = "";
		int max = 0;
		
		for(Map.Entry<String, Integer> entry: mapa.entrySet()) {
			if(entry.getValue() > max) {
				max = entry.getValue();
				vreme = entry.getKey();
			}
		}
		
		
		return vreme;
		
	}
	
	public static int brIstogVremena(String idPutnika, String vremePolaska) {
		
		int broj = 0;
		
		for(Polazak pol: polasci) {
			if(pol.getId_putnika().equalsIgnoreCase(idPutnika) && pol.getVreme_polaska().equalsIgnoreCase(vremePolaska) ) {
				broj += 1;
			}
		}
		
		return broj;
		
	}
	

	@SuppressWarnings("unchecked")
	public static int brRazKarata(Polazak polazak) {
			
		int broj = 0;
		
		Set<String> karte = new HashSet();
		
		for(Polazak pol: polasci) {
			
			if(pol.getId_putnika().equalsIgnoreCase(polazak.getId_putnika())) {
				if(!checkSet(karte, pol.getTip_karte())) {
					broj += 1;
					karte.add(pol.getTip_karte());
				}
			}
			
		}
		
		return broj;
		
	}
	
	
	public static boolean checkSet(Set<String> karte, String tipKarte) {
		
		boolean status = false;
		
		for(String karta: karte) {
			if(karta.equalsIgnoreCase(tipKarte)) {
				status = true;
			}
		}
		
		return status;
	}
	
	public static boolean checkIzvestaj(List<Izvestaj> izvestaji, Polazak polazak) {
		
		boolean status = false;
		
		for(Izvestaj izvestaj: izvestaji) {
			if(izvestaj.getIdPutnika().equalsIgnoreCase(polazak.getId_putnika())) {
				return true;
			}
		}
		
		return status;
	}
	
	
	
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public static List<Polazak> ucitajPolaske(String fileName) throws IOException{
		
		CSVReader csvReader = new CSVReader(new FileReader("src/files/" + fileName + ".csv"), ',' , '\'', 1);
		
		ColumnPositionMappingStrategy strategy = new ColumnPositionMappingStrategy<>();
		strategy.setType(Polazak.class);
		
		String [] kolone = new String [] {"id_putnika", "ime_prezime_putnika", "id_polaska", "datum_polaska", "vreme_polaska",
				"mesto_polaska", "mesto_dolaska", "tip_karte", "cena_karte"};
		
		strategy.setColumnMapping(kolone);
		
		CsvToBean csv = new CsvToBean<>();
		
		List<Polazak> polasci = csv.parse(strategy, csvReader);
		
		csvReader.close();
		
		return polasci;
	}
	
	public static void sacuvajIzvestaj(List<Izvestaj> izvestaj, String fileName) throws JsonGenerationException, JsonMappingException, IOException {
		
		ObjectMapper mapper = new ObjectMapper();
		
		mapper.writeValue(new File("src/files/" + fileName + ".json"), izvestaj);
		
	}
	
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static void upisiPolaskeCSV(List<Polazak> polasci, String fileName) throws IOException {
		
		CSVWriter csvWriter = new CSVWriter(new FileWriter("src/files/" + fileName + ".csv"), ',' , '\'', CSVWriter.NO_QUOTE_CHARACTER);
		
		ColumnPositionMappingStrategy strategy = new ColumnPositionMappingStrategy<>();
		strategy.setType(Polazak.class);
		
		String [] kolone = new String [] {"id_putnika", "ime_prezime_putnika", "id_polaska", "datum_polaska", "vreme_polaska",
				"mesto_polaska", "mesto_dolaska", "tip_karte", "cena_karte"};
		
		strategy.setColumnMapping(kolone);
		
		BeanToCsv csv = new BeanToCsv<>();
		
		csv.write(strategy, csvWriter, polasci);
		csvWriter.close();
		
	}
	
	public static void ispisiPolaske() {
		for(Polazak polazak: polasci) {
			System.out.println(polazak.toString());
		}
	}
	
	
	public static List<Polazak> createDate() {
		
		Polazak polazak1 = new Polazak("1", "Simon Mignolet", "1", "21.11.2017.", "11:00", "Novi Sad", "Beograd", "d", "150");
		Polazak polazak2 = new Polazak("2", "Alberto Moreno", "2", "21.11.2017.", "09:00", "Novi Sad", "Nis", "d", "200");
		Polazak polazak3 = new Polazak("3", "Joe Gomes", "3", "21.11.2017.", "12:00", "Novi Sad", "Pejicevi Salasi", "d", "160");
		Polazak polazak4 = new Polazak("4", "Joel Matip", "4", "21.11.2017.", "13:00", "Novi Sad", "Cacak", "d", "180");
		Polazak polazak5 = new Polazak("5", "Daniel Clyne", "5", "21.11.2017.", "11:00", "Novi Sad", "Temerin", "d", "80");
		Polazak polazak6 = new Polazak("6", "Nabi Keita", "6", "21.11.2017.", "15:00", "Novi Sad", "Beograd", "d", "120");
		Polazak polazak7 = new Polazak("7", "Juda Coutinho", "7", "21.11.2017.", "11:30", "Novi Sad", "Zrenjanin", "d", "100");
		Polazak polazak8 = new Polazak("8", "Adam Lallana", "8", "21.11.2017.", "11:00", "Novi Sad", "Beograd", "d", "120");
		Polazak polazak9 = new Polazak("9", "Mohamed Salah", "9", "21.11.2017.", "12:00", "Novi Sad", "Pancevo", "d", ".00");
		Polazak polazak10 = new Polazak("10", "Sadio Mane", "10", "22.11.2017.", "11:00", "Novi Sad", "Beograd", "d", "110");
		Polazak polazak11 = new Polazak("11", "Roberto Firminho", "11", "21.11.2017.", "11:00", "Novi Sad", "Vranje", "d", "400");
		
		Polazak polazak12 = new Polazak("1", "Simon Mignolet", "12", "24.11.2017.", "11:00", "Novi Sad", "Subotica", "d", "300");
		Polazak polazak13 = new Polazak("9", "Mohamed Salah", "13", "25.11.2017.", "15:00", "Novi Sad", "Somor", "g", "500");
		Polazak polazak14 = new Polazak("9", "Mohamed Salah", "14", "26.11.2017.", "15:00", "Novi Sad", "Valjevo", "m", "700");
		Polazak polazak15 = new Polazak("10", "Sadio Mane", "15", "27.11.2017.", "16:00", "Novi Sad", "Uzice", "g", "1000");
		
		List<Polazak> polasci = new ArrayList<Polazak>();
		
		polasci.add(polazak1);
		polasci.add(polazak2);
		polasci.add(polazak3);
		polasci.add(polazak4);
		polasci.add(polazak5);
		polasci.add(polazak6);
		polasci.add(polazak7);
		polasci.add(polazak8);
		polasci.add(polazak9);
		polasci.add(polazak10);
		polasci.add(polazak11);
		polasci.add(polazak12);
		polasci.add(polazak13);
		polasci.add(polazak14);
		polasci.add(polazak15);
		
		return polasci;
	}
	
}
