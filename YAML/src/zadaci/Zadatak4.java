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
		Yaml yaml = new Yaml();
		
		List<Log> logovi = new ArrayList<Log>();
		
		for(Object o: yaml.loadAll(input)){	
			System.out.println(o.getClass());
			if(o.getClass().toString().endsWith("Warning")){
				logovi.add((Log)o);
			}else if(o.getClass().toString().endsWith("Fatal")){
				logovi.add((Log)o);
			}
			else{
				//System.out.println("Error!");
			}
			
		}
		
	}

}
