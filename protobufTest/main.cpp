#include "protobufTest.h"
#include <QtWidgets/QApplication>
#include "glog/logging.h"

static void glogTest()
{
	int i = 0;
	char str[100] = "hello,log1234567890123456789qwerty123456789";
	LOG(INFO) << str;
	LOG(WARNING) << str;
	LOG(ERROR) << str;
	//FATAL等级日志程序会退出
	//LOG(FATAL) << str;
	LOG_IF(INFO, false) << str;
	LOG_IF(INFO, true) << str;
}
int main(int argc, char *argv[])
{
	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true;	
	FLAGS_log_dir = "d:\\Logs";	
	FLAGS_stderrthreshold = google::INFO;
	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true;
	FLAGS_minloglevel = google::INFO;
	FLAGS_max_log_size = 10;
	FLAGS_stop_logging_if_full_disk = true;
	google::InitGoogleLogging(argv[0]);
	
	google::SetStderrLogging(google::GLOG_INFO);

	QApplication a(argc, argv);
	protobufTest w;
	w.show();
	return a.exec();

	glogTest();

	
	google::ShutdownGoogleLogging();
}


