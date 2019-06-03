
/**
 * Ein Binaer Suchbaum wurde als Verlinkung der Knoten implementiert.
 * @author Quang Huy Nguyen, Michael Babic
 *
 * @param <T>
 */
public class verlinkungBaum<T extends Comparable<T>> implements Baum<T>{
	private Knoten<T> wurzel;
	private int count = 0;
	public verlinkungBaum ()
	{
		wurzel = null;
	}
	/**
	 * Fuegt ein Element in den Baum hinzu.
	 * @param elem das eingefuegte Element
	 * @return void
	 */
	public void insert (T elem)
	{
		if (wurzel == null)
		{
			wurzel = new Knoten<T>(elem);
		}
		else
		{
			insertRec (wurzel, elem);
		}
	}
	
	/**
	 * Fuegt ein Element in entsprechender Position im Baum ein.
	 * @param current aktuelle Knote in Suchbaum
	 * @param elem einzufuegte Element
	 */
	private void insertRec (Knoten<T> current, T elem)
	{
		if (current.getElem().compareTo(elem) < 0)
		{
			if (current.getRechts() == null)
			{
				current.setRechts(new Knoten<T>(elem));
				current.getRechts().setVater(current);
			}
			else
			{
				insertRec (current.getRechts(), elem);
			}
		}
		else if (current.getElem().compareTo(elem) > 0)		{
			if (current.getLinks() == null)
			{
				current.setLinks(new Knoten<T>(elem));
				current.getLinks().setVater(current);
			}
			else
			{
				insertRec (current.getLinks(), elem);
			}
		}
		else 
		{
			System.out.println("Knote wurde schon in Baum einzufuegt!");
		}
		//aktulisiert zus�tzliche Information f�r jede Knoten
		current.addierenInf((int) elem); 
	}
	
	/**
	 * Geben alle Knoten des Baum in Hauptreihenfolge aus.
	 * @param 
	 * @return
	 */
	public void preOrder ()
	{
		preOrderRec (wurzel);
	}
	
	/**
	 * Geben das gewissene Knote aus. 
	 * @param current aktuelle Knote
	 */
	private void preOrderRec (Knoten<T> current)
	{
		System.out.print(current.getElem() + " ");
		if (current.getLinks() != null)
		{
			preOrderRec (current.getLinks());
		}
		
		if (current.getRechts() != null)
		{
			preOrderRec (current.getRechts());
		}
	}
	
	/**
	 * Geben alle Knoten des Baum in symmetrisch aus.
	 * @param 
	 * @return
	 */
	public void inOrder ()
	{
		inOrderRec (wurzel);
	}
	
	/**
	 * Geben das gewissene Knote aus. 
	 * @param current aktuelle Knote
	 */
	private void inOrderRec (Knoten<T> current)
	{
		if (current.getLinks() != null)
		{
			inOrderRec (current.getLinks());
		}
		
		System.out.print(current.getElem() + " ");
		
		if (current.getRechts() != null)
		{
			inOrderRec (current.getRechts());
		}
	}
	
	/**
	 * Geben alle Knoten des Baum in Nebenreihenfolge aus.
	 * @param 
	 * @return
	 */
	public void postOrder ()
	{
		postOrderRec (wurzel);
	}
	
	/**
	 * Geben das gewissene Knote aus. 
	 * @param current aktuelle Knote
	 */
	private void postOrderRec (Knoten<T> current)
	{
		if (current.getLinks() != null)
		{
			postOrderRec (current.getLinks());
		}
		
		if (current.getRechts() != null)
		{
			postOrderRec (current.getRechts());
		}
		
		System.out.print(current.getElem() + " ");
	}

	/**
	 * Liefert die Summe der Knoten, die Intergerwert zwischen min und max haben, zur�ck.
	 * @param min der kleinste Wert eine Knote erreichen kann
	 * @param max der gro�este Wert eine Knote erreichen kann
	 * @return die gesuchte Summe
	 */
	public int summeBerechnen (int min, int max)
	{
		//im Worst Case, min und max Werte werden getauscht
		if(max < min) {
			count++;
			int tmp;
			tmp = max;
			max = min;
			min = tmp;
		}
		int sumWurzel, sumMin, sumMax, ergebnis;
		//Summe alle Knoten der BST
		sumWurzel = wurzel.additionInf;
		sumMin = summeKleinerAlsMin(wurzel, min);
		sumMax = summeGroesserAlsMax (wurzel, max);
		ergebnis = sumWurzel - sumMin - sumMax;
		return ergebnis;
	}
	
	/**
	 * Berechnet Summe der Knoten, die kleiner als min sind.
	 * @param current
	 * @param min
	 * @return 
	 */
	private int summeKleinerAlsMin (Knoten<T> current, int min)
	{
		count++;
		if (current == null)
		{
			return 0; // Abbruch Bedingung
		}
		else
		{
			if (current.getKey() > min) // Wenn current gr��er als min 
			{
				return summeKleinerAlsMin (current.getLinks(), min); // rekursiv mit linkem Sohn weiter
			}
			else if (current.getKey() == min) // Wenn current gleich min 
			{
				if (current.getLinks() == null)
				{
					return 0; // Abbruch Bedingung
				}
				else
				{
					return current.getLinks().additionInf; // gibt die zusatzInfo der linken Sohn zur�ck
				}
			}
			else // Wenn current kleiner als min 
			{
				int sum = current.getKey();
				if (current.getLinks() != null)
				{
					sum += current.getLinks().additionInf; // summe alle linken Sohne
					count++;
				}
				return sum + summeKleinerAlsMin(current.getRechts(), min); // update summe und rekursiv aufruf
			}
		}
	}
	
	/**
	 * Berechnet Summe der Knoten, die gr��er als max sind.
	 * @param current
	 * @param max
	 * @return 
	 */
	private int summeGroesserAlsMax (Knoten<T> current, int max)
	{
		count++;
		if (current == null)
		{
			return 0; // Abbruch Bedingung
		}
		else
		{
			if (current.getKey() < max) // Wenn current kleiner als max 
			{
				return summeGroesserAlsMax (current.getRechts(), max); // rekursiv mit rechtem Sohn weiter
			}
			else if (current.getKey() == max) // Wenn current gleich max 
			{
				if (current.getRechts() == null)
				{
					return 0; // Abbruch Bedingung
				}
				else
				{
					return current.getRechts().additionInf; // gibt die zusatzInfo der rechten Sohn zur�ck
				}
			}
			else // Wenn current gr��er als max 
			{
				int sum = current.getKey(); 
				if (current.getRechts() != null)
				{
					sum += current.getRechts().additionInf; // summe alle rechten Sohne
					count++;
				}
				return sum + summeGroesserAlsMax(current.getLinks(), max); // update summe und rekursiv aufruf
			}
		}
	}
	public int getCount ()
	{
		return count;
	}
	public void resetCount ()
	{
		count = 0;
	}
}
