package seqlist;

public class TestSeqList {

	public static void main(String[] args) {
		String[] chars = {"a", "h", "v", "r", "l"};
		SeqList<String> elements = new SeqList<String>(chars);
		
//		System.out.println("\ntestStatus:\nisEmpty:"+elements.isEmpty()+" size:"+elements.size()+" get(0):"+elements.get(0).toString()+" get(4):"+elements.get(4).toString());
//		
//		System.out.println("\ntestSet:\nbefore:get(2):"+elements.get(2).toString());
//		elements.set(2, "HaHa");
//		System.out.println("later:get(2):"+elements.get(2).toString());
//		
//		System.out.println("\ntestToString:\ntoString():"+elements.toString());
//		
//		System.out.println("\ntestInsert:\nbefore:"+elements.toString());
//		elements.insert(2, "Among");
//		System.out.println("later:"+elements.toString());
//		elements.insert("End");
//		System.out.println("finally:"+elements.toString());
//
//		System.out.println("\ntestRemove:\nbefore:"+elements.toString());
//		elements.remove(3);
//		System.out.println("later:"+elements.toString());
//		elements.clear();
//		System.out.println("finally:"+elements.toString());
		
		System.out.println("\nsearch:\nsearch v: " + elements.search("v"));
		System.out.println("contain a: " + elements.contains("a") + " contain haha: " + elements.contains("haha"));
		
		System.out.println("\ninsertDifferent:\ninsert uhhh: " + elements.insertDifferent("uhhh") + " insert v: " + elements.insertDifferent("v"));
		
		System.out.println("\nremove:\n" + "before: " + elements.toString());
		System.out.println("delete " + elements.remove("v"));
		System.out.println("later: " + elements.toString());
		
		String[] chars1 = {"b", "h", "v", "r", "l"};
		String[] chars2 = {"a", "h", "r", "l", "uhhh"};
		
		SeqList<String> lista = new SeqList<String>(chars1);
		SeqList<String> listb = new SeqList<String>(chars2);
		
		System.out.println("\nequals:");
		System.out.println("elements vs lista: " + elements.equals(lista) + " elements vs listb: " + elements.equals(listb));
		
		System.out.println("\naddAll:");
		System.out.println("before: " + elements.toString());
		elements.addAll(lista);
		System.out.println("latter: " + elements.toString());
	}
}
