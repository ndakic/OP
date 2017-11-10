package zad3;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import zad1.Podatak;
import zad1.Zadatak1;
import zad2.Zadatak2;

public class Zadatak3 {
	
	public static List<Podatak> podaci;

	public static void main(String[] args) throws Exception {
		
		podaci = Zadatak1.createCSV("podaci");
		
		Set<String> setSa = new HashSet<String>();
		Set<String> setBez = new HashSet<String>();
		
		List<Podatak> saPovratkom = new ArrayList<>();
		List<Podatak> bezPovratka = new ArrayList<>();
		
		for(Podatak pod: podaci) {
			Podatak podatak = obezPovratak(pod.getMestoPolaska(), pod.getMestoDolaska());
			
			if(podatak != null) {
				setSa.add(podatak.getSifraRelacije());
			}else {
				setBez.add(pod.getSifraRelacije());
			}
		}
		
		for(String s: setSa) {
			Podatak pod = getPodatak(s);
			saPovratkom.add(pod);
		}
		
		for(String b: setBez) {
			Podatak pod = getPodatak(b);
			bezPovratka.add(pod);
		}
		
		Zadatak2.saveToYAML(saPovratkom, "relacijeSaPovratkom");
		saveToJSON(bezPovratka, "relacijeBezPovratka");

	}
	
	public static Podatak obezPovratak(String pol, String dol) {
		
		Podatak pod = null;
	
		for(Podatak podatak: podaci) {
			if(podatak.getMestoPolaska().equalsIgnoreCase(dol) && podatak.getMestoDolaska().equalsIgnoreCase(pol)) {
				pod = podatak;
			}
		}
			
		return pod;
	}
	
	public static Podatak getPodatak(String sifraRelacije) {
		
		Podatak podatak = null;
		
		for(Podatak pod: podaci) {
			if(pod.getSifraRelacije().equalsIgnoreCase(sifraRelacije)) {
				podatak = pod;
			}
		}
		
		return podatak;
		
	}
	
	public static void saveToJSON(List<Podatak> podaci, String fileName) throws Exception, JsonProcessingException, Exception {
		
		ObjectMapper mapper = new ObjectMapper();
		mapper.writeValue(new File("src/files/" + fileName + ".json"), podaci);
		
	}

}
