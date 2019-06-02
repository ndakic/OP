package zad6;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.DumperOptions.FlowStyle;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import au.com.bytecode.opencsv.CSVWriter;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;

public class Bioskop {
	
	public static List<Projekcija> projekcije = null;

	public static void main(String[] args) throws IOException {
		
		createDataYAML("projekcije");
			
		// Projekcija projekcija = ucitajProjekciju();
		//projekcije = ucitajViseYAMLfajlova();
		
		projekcije = ucitajProjekcije();
		
		//ispisiProjekcije();
			
		List<Izvestaj> izvestaji = new ArrayList<>();
		
		for(Projekcija projekcija: projekcije) {
			
			if(!customContains(izvestaji, projekcija)) {
				
				int najK = najkracaProjekcija(projekcija);
				int najD = najduzaProjekcija(projekcija);
				double prosek = prosecnoTrajProjekcije(projekcija);
				
				Izvestaj izvestaj = new Izvestaj(projekcija.getSifraSale(), projekcija.getNazivSale(), 
						Integer.toString(najK), Integer.toString(najD), Double.toString(prosek), projekcija.getDatum());
				
				izvestaji.add(izvestaj);
			}
		}
		
		Collections.sort(izvestaji);
		
		saveToJson(izvestaji, "izvestaji");
		
		
		ucitajIzvestaje();
		
	}
	
	
	public static int najkracaProjekcija(Projekcija projekcija) {
			
		int min = 999999;
		
		for(Projekcija pro: projekcije) {
			if(pro.getSifraSale().equalsIgnoreCase(projekcija.getSifraSale()) && pro.getDatum().equalsIgnoreCase(projekcija.getDatum())) {
				if(Integer.parseInt(pro.getTrajanje()) < min) {
					min = Integer.parseInt(pro.getTrajanje());
				}
			}
		}
		
		return min;
		
	}
	
	public static int najduzaProjekcija(Projekcija projekcija) {
		
		int min = 0;
		
		for(Projekcija pro: projekcije) {
			if(pro.getSifraSale().equalsIgnoreCase(projekcija.getSifraSale()) && pro.getDatum().equalsIgnoreCase(projekcija.getDatum())) {
				if(Integer.parseInt(pro.getTrajanje()) > min) {
					min = Integer.parseInt(pro.getTrajanje());
				}
			}
		}
		
		return min;
		
	}
	
	public static double prosecnoTrajProjekcije(Projekcija projekcija) {
		
		double suma = 0;
		double n = 0;
		
		for(Projekcija pro: projekcije) {
			if(pro.getSifraSale().equalsIgnoreCase(projekcija.getSifraSale()) && pro.getDatum().equalsIgnoreCase(projekcija.getDatum())) {
				
				suma += Integer.parseInt(pro.getTrajanje());
				n += 1;
				
			}
		}
		
		return suma / n;
		
	}
	
	
	public static void ispisiProjekcije() {
		
		for(Projekcija pro: projekcije) {
			System.out.println(pro.toString());
		}
		
	}
	
	
	public static boolean customContains(List<Izvestaj> izvestaji, Projekcija projekcija) {
		
		boolean stanje = false;
		
		for(Izvestaj izvestaj: izvestaji) {
			if(izvestaj.getSifraSale().equalsIgnoreCase(projekcija.getSifraSale()) && izvestaj.getDatum().equalsIgnoreCase(projekcija.getDatum()))
				stanje = true;
		}
				
		return stanje;
		
	}
	
	


	
	
//	=====================================================================


	public static List<Izvestaj> ucitajIzvestaje() throws JsonParseException, JsonMappingException, IOException{
		
		ObjectMapper objectMapper = new ObjectMapper();
		
		List<Izvestaj> izvestaji = Arrays.asList(objectMapper.readValue(new File("src/files/izvestaji.json"), Izvestaj[].class));
		
		for(Izvestaj iz: izvestaji)
			System.out.println(iz.toString());
		
		return izvestaji;
		
	}
		
	
	@SuppressWarnings({ "unused", "unused" })
	public static void saveToJson(List<Izvestaj> izvestaji, String fileName) throws JsonGenerationException, JsonMappingException, IOException {
		
		ObjectMapper objectMapper = new ObjectMapper();
		
		objectMapper.writeValue(new File("src/files/" + fileName + ".json"), izvestaji);
		
	}
	
	@SuppressWarnings("unchecked")
	public static List<Projekcija> ucitajProjekcije() throws FileNotFoundException{
			
		InputStream input = new FileInputStream(new File("src/files/projekcije.yaml"));
		
		Yaml yaml = new Yaml();
		
		Iterable<Object> iter =  yaml.loadAll(input);
		
		List<Projekcija> projekcije = null;
		
		for(Object obj: iter) {
			//System.out.println(obj.getClass());
			projekcije = (List<Projekcija>) obj;
			
		}
		
		return projekcije;
	}
	
	public static Projekcija ucitajProjekciju() throws FileNotFoundException {
		
		InputStream input = new FileInputStream(new File("src/files/projekcije2.yaml"));
		
		Yaml yaml = new Yaml(new Constructor(Projekcija.class));
		
		Projekcija proj = (Projekcija) yaml.load(input);
		
		System.out.println(proj.toString());
				
		return proj;
		
	}
	
	@SuppressWarnings("unchecked")
	public static List<Projekcija> ucitajViseYAMLfajlova() throws FileNotFoundException{
		
		List<Projekcija> projekcije = new ArrayList();
		
		
		InputStream input = new FileInputStream(new File("src/files/projViseDoc.yaml"));
		
		Yaml yaml = new Yaml();
		
		ObjectMapper objectMapper = new ObjectMapper();
		
		for(Object obj: yaml.loadAll(input)) {
			
			Projekcija pro = objectMapper.convertValue(obj, Projekcija.class);
			
			projekcije.add(pro);
			
		}
		
		
		return projekcije;
		
	}
	

	public static void createDataYAML(String fileName) throws IOException {
		
		DumperOptions dumperOptions = new DumperOptions();
		dumperOptions.setDefaultFlowStyle(FlowStyle.BLOCK);
		
		Yaml yaml = new Yaml(dumperOptions);
		
		List<Projekcija> data = createData();	
		
		// upisati svaki objekat kao poseban YAML dokument u istom fajlu
		//yaml.dumpAll(data.iterator(), new FileWriter("src/files/projViseDoc.yaml")); 
		
		yaml.dump(data, new FileWriter("src/files/" + fileName + ".yaml"));
		
	}
	
	public static List<Projekcija> createData(){
		
		Projekcija projekcija1 = new Projekcija("1", "Velika Sala", "20.11.2017.", "21:00", "110", "Matilda" );
		Projekcija projekcija13 = new Projekcija("1", "Velika Sala", "20.11.2017.", "14:00", "120", "Matilda2" );
		Projekcija projekcija14 = new Projekcija("1", "Velika Sala", "21.11.2017.", "15:00", "125", "Matilda3" );
		Projekcija projekcija2 = new Projekcija("2", "Mala Sala", "21.11.2017.", "21:00", "100", "Cetvrti covek");
		Projekcija projekcija3 = new Projekcija("3", "Velika Sala", "21.11.2017.", "18:00", "120", "Lepa sela lepo gore");
		Projekcija projekcija31 = new Projekcija("3", "Velika Sala", "22.11.2017.", "10:00", "90", "Lepa sela lepo gore");
		Projekcija projekcija32 = new Projekcija("3", "Velika Sala", "22.11.2017.", "14:00", "70", "Lepa sela lepo gore");
		Projekcija projekcija33 = new Projekcija("3", "Velika Sala", "22.11.2017.", "22:00", "125", "Lepa sela lepo gore");
		Projekcija projekcija4 = new Projekcija("4", "Elite Sala", "23.11.2017.", "21:00", "130", "Klopka");
		Projekcija projekcija5 = new Projekcija("5", "Mala Sala", "24.11.2017.", "21:00", "105", "Nebeska udica");
		Projekcija projekcija6 = new Projekcija("6", "Velika Sala", "25.11.2017.", "21:00", "110", "Munje");
		Projekcija projekcija7 = new Projekcija("7", "Mala Sala", "26.11.2017.", "19:00", "115", "Kad porastem bicu kengur");
		Projekcija projekcija8 = new Projekcija("5", "Elite Sala", "24.11.2017.", "12:00", "110", "Hobbit");
		Projekcija projekcija9 = new Projekcija("3", "Velika Sala", "22.11.2017.", "10:00", "130", "Ko to tamo peva");
		Projekcija projekcija10 = new Projekcija("2", "Mala Sala", "21.11.2017.", "16:00", "90", "Ubistvo u Orijent Ekspresu");
		Projekcija projekcija11 = new Projekcija("4", "Velika Sala", "23.11.2017.", "16:00", "95", "Balkanski spijun");
		Projekcija projekcija12 = new Projekcija("7", "Elite Sala", "26.11.2017.", "22:00", "110", "Varljivo leto 68");
		
		List<Projekcija> projekcije = new ArrayList();
		
		projekcije.add(projekcija1);
		projekcije.add(projekcija2);
		projekcije.add(projekcija3);
		projekcije.add(projekcija4);
		projekcije.add(projekcija5);
		projekcije.add(projekcija6);
		projekcije.add(projekcija7);
		projekcije.add(projekcija8);
		projekcije.add(projekcija9);
		projekcije.add(projekcija10);
		projekcije.add(projekcija11);
		projekcije.add(projekcija12);
		projekcije.add(projekcija13);
		projekcije.add(projekcija14);
		
		projekcije.add(projekcija31);
		projekcije.add(projekcija32);
		projekcije.add(projekcija33);
		
		return projekcije;
		
	}

}
