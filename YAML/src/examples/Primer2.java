package examples;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import org.yaml.snakeyaml.Yaml;

public class Primer2 {

	public static void main(String[] args) throws FileNotFoundException{
		
		InputStream input = new FileInputStream(new File("src/files/log.yaml"));
		Yaml yaml = new Yaml();
		int counter = 0;
		for (Object data : yaml.loadAll(input)) {
			System.out.println(data);
		counter++;
		
		}
		System.out.println("documents: "+counter);

	}

}
