package zad5;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import au.com.bytecode.opencsv.CSVWriter;
import au.com.bytecode.opencsv.bean.BeanToCsv;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;

public class Zadatak5 {
	
	public static List<Rent> rentPodaci = null;

	@SuppressWarnings("unused")
	public static void main(String[] args) throws JsonGenerationException, JsonMappingException, IOException {
		
		
		//napraviJSON(data(), "rent");
		
		rentPodaci = ucitajRentPodatke("rent");
		
		mesecGodIznajmljivanja("10", "2017", "iznPoMesIGod"); // 1
				
		saveToCVS(calSumaProsek(), "sumaProsek"); // 2
		
		Collections.sort(rentPodaci);
		
		napraviJSON(rentPodaci, "sortiraniPodaci"); // 3
		
	}
	
	
	public static List<SumaProsek> calSumaProsek(){
		
		List<SumaProsek> sumaProsek = new ArrayList<>();
		List<Rent> temp = new ArrayList<>();
		
		for(Rent r: rentPodaci) {	
			if(!customContains(temp, r)) {
		
				int ukupnaS = izrPotrosenuSumu(r);
				double pros = prosecanBrDanaIzn(r);
				
				sumaProsek.add(new SumaProsek(r.getOsoba().getMaticniBroj(), Integer.toString(ukupnaS), Double.toString(pros)));
				
				temp.add(r);
			}
		}
		
		return sumaProsek;
		
	}
	
	
	public static void mesecGodIznajmljivanja(String mesec, String godina, String fileName) throws IOException {
		
		List<Rent> iznMG = new ArrayList<>();
		
		for(Rent r: rentPodaci) {
						
			String [] datum = r.getDatumIzn().split("\\.");
			
			if(datum[1].equalsIgnoreCase(mesec) && datum[2].equalsIgnoreCase(godina))
				iznMG.add(r);
				
		}
		
		DumperOptions dumperOptions = new DumperOptions();
		dumperOptions.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
		
		Yaml yaml = new Yaml(dumperOptions);
		yaml.dump(iznMG, new FileWriter("src/files/" + fileName + ".yaml"));
		
		
	}
	
	public static int izrPotrosenuSumu(Rent rent) {
		int suma = 0;
		
		for(Rent r: rentPodaci) {
			if(r.compareObjectsToByOsoba(rent) == 0) {
				suma += Integer.parseInt(r.getBrojIznDana()) * Integer.parseInt(r.getCenaIznNaDan());
			}
		}
		
		return suma;
	}
	
	public static double prosecanBrDanaIzn(Rent rent) {
		
		int ukupnoIzn = 0;
		double suma = 0;
		
		for(Rent r: rentPodaci) {
			if(r.compareObjectsToByOsoba(rent) == 0) {
				suma += Integer.parseInt(r.getBrojIznDana());
				ukupnoIzn += 1;
			}
		}
				
		return suma / ukupnoIzn;
	}
	
	public static boolean customContains(List<Rent> rents, Rent r) {
		
		boolean status = false;
		
		for(Rent rent: rents) {
			if(rent.compareObjectsToByOsoba(r) == 0)
				status = true;
		}
		
		return status;
	} 



	
	
	
	
//	================================================================
// 							READ/WRITE			
//	================================================================
	
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static void saveToCVS(List<SumaProsek> sumaProsek, String fileName) throws IOException {
		
		CSVWriter writer = new CSVWriter(new FileWriter("src/files/" + fileName + ".csv"), ',', CSVWriter.NO_QUOTE_CHARACTER);
		
		ColumnPositionMappingStrategy strategy = new ColumnPositionMappingStrategy<>();
		strategy.setType(SumaProsek.class);
		
		String [] columns = new String [] {"matBrOsobe", "potrosenaSuma", "prosekDana"};
		strategy.setColumnMapping(columns);
		
		BeanToCsv csv = new BeanToCsv<>();
		
		csv.write(strategy, writer, sumaProsek);
		
		writer.close();
		
	}
	
	
	
	public static List<Rent> ucitajRentPodatke(String fileName) throws JsonParseException, JsonMappingException, IOException{
		
		ObjectMapper mapper = new ObjectMapper();
		List<Rent> rent = Arrays.asList(mapper.readValue(new File("src/files/" + fileName + ".json"), Rent[].class));
		
		return rent;
		
	}
	
	
	public static void napraviJSON(List<Rent> lista,  String fileName) throws JsonGenerationException, JsonMappingException, IOException {
		
		ObjectMapper mapper = new ObjectMapper();
		mapper.writeValue(new File("src/files/" + fileName +".json"), lista);
		
	}
	
	public static List<Rent> data(){
			
		Osoba osoba1 = new Osoba("Nikola", "Lazic", "1");
		Osoba osoba2 = new Osoba("Milos", "Teodosic", "2");
		Osoba osoba3 = new Osoba("Novica", "Velickovic", "3");
		Osoba osoba4 = new Osoba("Nikola", "Jokic", "4");
		Osoba osoba5 = new Osoba("Bogdan", "Bogdanovic", "5");
		
		Rent rent1 = new Rent("1", "Novi Sad", "11.10.2017.", "31.10.2017.", "1000", "10000", "21", osoba1);
		Rent rent2 = new Rent("2", "Beograd", "14.10.2017.", "31.10.2017.", "1200", "10000", "18", osoba2);
		Rent rent3 = new Rent("3", "Novi Sad", "16.12.2017.", "31.12.2017.", "1100", "10000", "16", osoba3);
		Rent rent4 = new Rent("4", "Beograd", "18.10.2017.", "31.10.2017.", "1050", "10000", "14", osoba4);
		Rent rent5 = new Rent("5", "Novi Sad", "19.11.2017.", "31.11.2017.", "1300", "10000", "13", osoba1);
		
		List<Rent> rentPodaci = new ArrayList<>();
		
		rentPodaci.add(rent1);
		rentPodaci.add(rent2);
		rentPodaci.add(rent3);
		rentPodaci.add(rent4);
		rentPodaci.add(rent5);
		
		return rentPodaci;
	}
	
}
