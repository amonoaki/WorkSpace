package actioninterface;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFileChooser;
import userinterface.*;

public class ProcessFile implements ActionListener {

	JFileChooser jFileChooser = new JFileChooser();  //创建文件选择类准备创建文件对话框
	Layout layout = new Layout();
	
	@Override
	public void actionPerformed(ActionEvent e) {
		int status = -1;
		if (e.getSource() == layout.getOpenFile()) {  //点击了 打开文件 对话框
			status = jFileChooser.showOpenDialog(layout.getTextAreaPage());  //创建对话框，在页面居中显示
			if (status == JFileChooser.APPROVE_OPTION) {
				//打开文件，显示于新标签页，注意异常处理。
			}
		}
		else if (e.getSource() == layout.getSaveFile()) {
			status = jFileChooser.showSaveDialog(layout.getTextAreaPage());  //创建对话框，在页面居中显示
			if (status == JFileChooser.APPROVE_OPTION) {
				//保存文件，注意异常处理。注意是否已经保存过这一文件。
			}
		}
		else if (e.getSource() == layout.getNewFile()) {
			layout.createTab("newfile"+layout.getNewFileCount(), "");
		}
	}

}
