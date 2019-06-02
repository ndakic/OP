package zadaci;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.InputStream;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import examples.Invoice;
import examples.Person;
import examples.Product;

public class Zadatak2 {

	@SuppressWarnings("unused")
	public static void main(String[] args) throws Exception {
		
		InputStream input = new FileInputStream(new File("src/files/invoice.yaml"));
		Yaml yaml = new Yaml(new Constructor(Invoice.class));
		
		Invoice invoice = (Invoice) yaml.load(input);
		
		InputStream input2 = new FileInputStream(new File("src/files/exchange.yaml"));
		Yaml yaml2 = new Yaml(new Constructor(Exchange.class));
		
		
		Exchange kurs = (Exchange) yaml2.load(input2);
		
		
		for(Product prod: invoice.getProduct()){
			prod.setPrice(prod.getPrice() * kurs.getDin());
		}
		
		invoice.setTax(invoice.getTax() * kurs.getDin());
		invoice.setTotal(invoice.getTotal() * kurs.getDin());
		
		System.out.println(invoice.toString());
		
		String din = "din";
		String dolar = "dolar";
		

		DumperOptions opts = new DumperOptions();
		opts.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
		
		Yaml yamlw = new Yaml(opts);
		yamlw.dump(invoice, new FileWriter(new File("src/files/invoice_" + din + ".yaml")));

	}

}
