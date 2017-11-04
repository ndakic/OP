package zadaci;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import examples.Invoice;
import examples.Product;

public class Zadatak3 {

	@SuppressWarnings({ "unused", "rawtypes", "unchecked" })
	public static void main(String[] args) throws Exception {
		
		InputStream input = new FileInputStream(new File("src/files/invoice.yaml"));
		Yaml yaml = new Yaml(new Constructor(Invoice.class));
		
		Invoice invoice = (Invoice) yaml.load(input);
		
		int brojac = 1;
		int brFakture = invoice.getInvoice() + 1;
		
		DumperOptions opts = new DumperOptions();
		opts.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
		
		Yaml yamlw = new Yaml(opts);
		
		for(Product prod: invoice.getProduct()){
			List<Product> products = new ArrayList();
			products.add(prod);
			invoice.setProduct(products);
			invoice.setInvoice(brFakture);
		
			invoice.setTotal((prod.getPrice() * prod.getQuantity()) + invoice.getTax());
			
			yamlw.dump(invoice, new FileWriter(new File("src/files/invoice_" +brojac + ".yaml")));
			brojac +=1;
			brFakture +=1;
		}

	}

}
