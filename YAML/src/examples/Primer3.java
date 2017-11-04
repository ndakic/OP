package examples;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

public class Primer3 {

	public static void main(String[] args) throws Exception {
		
		InputStream input = new FileInputStream(new File("src/files/invoice.yaml"));
		Yaml yaml = new Yaml(new Constructor(Invoice.class));
		
		Invoice invoice = (Invoice) yaml.load(input);
		Person person = invoice.getBillTo();
			
		System.out.println(invoice.toString());
		
	}

}
