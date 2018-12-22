package zad4;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;
import org.yaml.snakeyaml.introspector.Property;
import org.yaml.snakeyaml.nodes.NodeTuple;
import org.yaml.snakeyaml.nodes.Tag;
import org.yaml.snakeyaml.representer.Representer;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import au.com.bytecode.opencsv.CSVReader;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;
import au.com.bytecode.opencsv.bean.CsvToBean;
import zad1.Podatak;

public class Zadatak4 {

	public static void main(String[] args) throws IOException {
		
		
		List<Podatak> podaci = getCSVPodatke();
		
		//createYAMLFile();
		
		List<Podatak> pretraga = search(podaci);
		
		saveToJSON(pretraga, "pretraga");
		
		
		

	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static List<Podatak> getCSVPodatke() throws FileNotFoundException{
		
		
		CSVReader csvReader = new CSVReader(new FileReader("src/files/podaci.csv"),',','\'', 1);
		
		ColumnPositionMappingStrategy strat = new ColumnPositionMappingStrategy<>();
		strat.setType(Podatak.class);
		
		String [] columns = new String[] {"sifraRelacije", "mestoPolaska", "mestoDolaska",  
				"datumPolaska", "vremePolaska", "planiranoVremeDolaska", "peronPolaska", "cenaKarte", "brProdKarata", "brRelacija"};
		
		strat.setColumnMapping(columns);
		
		CsvToBean csvToBean = new CsvToBean();
		
		List<Podatak> podaci = csvToBean.parse(strat, csvReader);
		

		return podaci;
		
	}
	
	public static void createYAMLFile() throws IOException {
		
		Podatak pod1 = new Podatak();
		pod1.setMestoPolaska("Sombor");
		pod1.setCenaKarte("500");
		
		DumperOptions opts = new DumperOptions();
		opts.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
		
		Yaml yaml = new Yaml(representer, opts);
		yaml.dump(pod1, new FileWriter("src/files/data.yaml"));
		
	}
	
	public static Podatak readFromYAML() throws FileNotFoundException {
		
		Yaml yaml = new Yaml(new Constructor(Podatak.class));
		Podatak pod = (Podatak) yaml.load(new FileReader("src/files/data.yaml")); 
				
		return pod;
	}
	
	
	@SuppressWarnings({ "rawtypes", "unchecked", "unused" })
	public static List<Podatak> search(List<Podatak> podaci) throws FileNotFoundException{
		
		List<Podatak> pretraga = new ArrayList();
		Podatak pod = readFromYAML();

		for(Podatak podatak: podaci) {
			if(podatak.compareTo(pod) == 0) {
				pretraga.add(podatak);
			}
		}
		
		return pretraga;
	}
	
	public static void saveToJSON(List<Podatak> podaci, String fileName) throws JsonGenerationException, JsonMappingException, IOException {
		
		ObjectMapper objectMapper = new ObjectMapper();
		
		objectMapper.writeValue(new FileWriter("src/files/" + fileName +".json"), podaci);
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
	


}
