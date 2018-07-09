package mylistenner;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import userinterface.Layout;

public class TabButtonListenner implements ActionListener {

	private Layout layout;
		
	public TabButtonListenner(Layout layout) {
		super();
		this.layout = layout;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		JButton button = (JButton)e.getSource();
		layout.deleteTabNamed(button.getToolTipText().substring(6));   //tooltip从第6位到最后即为标签页名字
	}
}
