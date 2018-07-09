package mylistenner;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;
import javax.swing.JPanel;

import userinterface.Layout;

public class TabPanelListener implements MouseListener {
	
	private Layout layout;


	public TabPanelListener(Layout layout) {
		super();
		this.layout = layout;
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		JPanel tabPanel = (JPanel)e.getComponent();
		layout.setActiveTabNamed(tabPanel.getToolTipText());
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		

	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		JButton tabButton = null;
				
		if (e.getSource() instanceof JButton) {
			tabButton = (JButton)e.getComponent();
		}
		else if (e.getSource() instanceof JPanel) {
			JPanel tabPanel = (JPanel)e.getComponent();
			tabButton = (JButton)tabPanel.getComponent(1);
		}
        tabButton.setContentAreaFilled(true);  //取消透明化
        tabButton.setBorderPainted(true);  //显示边界
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		JButton tabButton = null;
		
		if (e.getSource() instanceof JButton) {
			tabButton = (JButton)e.getComponent();
		}
		else if (e.getSource() instanceof JPanel) {
			JPanel tabPanel = (JPanel)e.getComponent();
			tabButton = (JButton)tabPanel.getComponent(1);
		}
        tabButton.setContentAreaFilled(false);  //填充透明化
        tabButton.setBorderPainted(false);  //取消边界显示
	}

}
