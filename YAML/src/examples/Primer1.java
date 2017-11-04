package examples;

import java.util.List;

import org.yaml.snakeyaml.Yaml;

public class Primer1 {

	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		
		Yaml yaml = new Yaml();
		String document = "\n- A\n- B\n- C";
		List<String> list = (List<String>) yaml.load(document);
		
		for(String s: list) {
			System.out.println(s);
		}
		
	}

}
