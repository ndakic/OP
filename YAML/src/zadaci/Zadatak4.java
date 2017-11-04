package zadaci;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;
import org.yaml.snakeyaml.constructor.SafeConstructor;

public class Zadatak4 {

	@SuppressWarnings("unused")
	public static void main(String[] args) throws Exception {
	
		InputStream input = new FileInputStream(new File("src/files/log.yaml"));
		Yaml yaml = new Yaml(new Constructor(Log.class));
		//Yaml yaml = new Yaml(); Ovako prođe parsiranje, međutim dobijem da je Objekat tipa LinkedHashMap prilikom poziva o.getClass(), a sa njim ne mogu nista posle
		// pročitah da moram na ovaj nacin : (Yaml yaml = new Yaml(new Constructor(Log.class));), ali neće iz nekog razloga da ucita podatke kako treba
		// The loadAll will indeed load all documents as person/Log objects. But I have to cast them manually. - Probah i ovaj njegov primer al nece ni on
		
		List<Log> logovi = new ArrayList<Log>();
		
		for(Object o: yaml.loadAll(input)){	// ovde odmah puca prilikom ucitavanja
			System.out.println(o.getClass());
//			if(o.getClass().toString().endsWith("Warning")){
//				logovi.add((Log)o);
//			}else if(o.getClass().toString().endsWith("Fatal")){
//				logovi.add((Log)o);
//			}
//			else{
//				//System.out.println("Error!");
//			}
			
		}
		
//		InputStream input2 = new FileInputStream(new File("src/files/test.yaml"));
//		Yaml yaml2 = new Yaml(new Constructor(Person.class));
//		
//		ArrayList<Person> persons = new ArrayList<Person>();
//		
//		for(Object o: yaml2.loadAll(input2)){	
//			System.out.println(o.getClass());
//			if (o.getClass().toString().endsWith("Person")) {
//			    persons.add((Person) o);
//			  } else {
//			    System.out.println("Error reading Person.");
//			  }
//
//		}
		
	}

}
