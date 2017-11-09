package zad2;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.introspector.Property;
import org.yaml.snakeyaml.nodes.NodeTuple;
import org.yaml.snakeyaml.nodes.Tag;
import org.yaml.snakeyaml.representer.Representer;

import zad1.Podatak;
import zad1.Zadatak1;

public class Zadatak2 {
	
	private static List<Podatak> podaci;

	@SuppressWarnings("unused")
	public static void main(String[] args) throws IOException {
		
		podaci = Zadatak1.createCSV("podaci");
		
		HashMap<String, Integer> mapa = new HashMap<>();
		
		for(Podatak podatak: podaci) {
			
			int broj = count(podatak.getSifraRelacije());
			mapa.put(podatak.getSifraRelacije(), broj);
			
		}
		
		Podatak najvisePolazaka = najvisePolazaka(mapa);
		Podatak najDuza = najDuzaRelacija();
		Podatak najIspl = najIsplatljivija();
		
		List<Podatak> podaciYAML = new ArrayList<>();
		podaciYAML.add(najvisePolazaka);
		podaciYAML.add(najDuza);
		podaciYAML.add(najIspl);
		
		saveToYAML(podaciYAML, "podaci");
		
			
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
		
		saveToYAML(saPovratkom, "relacijeSaPovratkom");
		saveToYAML(bezPovratka, "relacijeBezPovratka");
					
	}
	
	public static int count(String sifraRelacije) {
		
		int brojac = 0;
		
		for(Podatak pod: podaci) {
			if(pod.getSifraRelacije().equalsIgnoreCase(sifraRelacije)) {
				brojac += 1;
			}
		}
			
		return brojac;
	}
	
	public static Podatak najvisePolazaka(HashMap<String, Integer> mapa) {
		
		String sifra = "";
		int max = 0;
		
		for(Map.Entry<String, Integer> entry: mapa.entrySet()) {
			if(entry.getValue() > max) {
				max = entry.getValue();
				sifra = entry.getKey();
			}
		}
		
		Podatak podatak = getPodatak(sifra);
		
		if(max != 0)
			podatak.setBrRelacija(max);
		
		return podatak;
				
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
	
	public static Podatak najDuzaRelacija() {
		
		Podatak podatak = null;
		
		int naj = 0;
		
		for(Podatak pod: podaci) {
			
			String [] vremePol = pod.getVremePolaska().split(":");
			String [] vremeDol = pod.getPlaniranoVremeDolaska().split(":");
			
			int vremePolUMin = Integer.parseInt(vremePol[0]) * 60  + Integer.parseInt(vremePol[1]); 
			int vremeDolUMin = Integer.parseInt(vremeDol[0]) * 60  + Integer.parseInt(vremeDol[1]); 
			
			int uporedi = vremeDolUMin - vremePolUMin;
			
			if(uporedi > naj) {
				naj = uporedi;
				podatak = pod;
			}
			
		}
				
		return podatak;
		
	}
	
	public static Podatak najIsplatljivija() {
		
		Podatak podatak = null;
		
		int naj = 0;
		
		for(Podatak pod: podaci) {
			int zarada = pod.getCenaKarte() * pod.getBrProdKarata();
			
			if(zarada > naj) {
				naj = zarada;
				podatak = pod;
			}
		}
		
		
		return podatak;
		
	}
	
	@SuppressWarnings({ "unused", "rawtypes", "unchecked" })
	public static void saveToYAML(List<Podatak> podaciYAML, String fileName) throws IOException {
		
		
	    DumperOptions opts = new DumperOptions();
		opts.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
	
		Yaml yamlw = new Yaml(representer, opts);
		yamlw.dump(podaciYAML, new FileWriter(new File("src/files/" + fileName + ".yaml")));
	    
		
	}
	
	static Representer representer = new Representer() {
	    @Override
	    protected NodeTuple representJavaBeanProperty(Object javaBean, Property property, Object propertyValue,Tag customTag) {
	        // if value of property is null, ignore it.
	    	
	        if (propertyValue == null || propertyValue.equals(0)) {
	            return null;
	        }  
	        else {
	            return super.representJavaBeanProperty(javaBean, property, propertyValue, customTag);
	        }
	        
  
	    }
	};
	
	public static Podatak obezPovratak(String pol, String dol) {
		
		Podatak pod = null;
	
		for(Podatak podatak: podaci) {
			if(podatak.getMestoPolaska().equalsIgnoreCase(dol) && podatak.getMestoDolaska().equalsIgnoreCase(pol)) {
				pod = podatak;
			}
		}
			
		return pod;
	}
	
	

}
