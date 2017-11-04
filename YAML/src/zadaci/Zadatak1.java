package zadaci;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.InputStream;
import java.util.Scanner;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import examples.Invoice;
import examples.Person;

public class Zadatak1 {

	public static void main(String[] args) throws Exception{
		

		
		InputStream input = new FileInputStream(new File("src/files/invoice.yaml"));
		Yaml yaml = new Yaml(new Constructor(Invoice.class));
		
		Invoice invoice = (Invoice) yaml.load(input);
		Person person = invoice.getBillTo();
		
		Scanner reader = new Scanner(System.in);  
		System.out.println("Unesite novu adresu: ");
		String adresa = reader.nextLine(); 

		reader.close();
		
		person.getAddress().setLines(adresa);
		System.out.println(person.toString());
		
		
		DumperOptions opts = new DumperOptions();
		opts.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
		
		Yaml writeYaml = new Yaml(opts);
		
		
		writeYaml.dump(invoice, new FileWriter(new File("src/files/invoice_mod.yaml")));

	}

}
