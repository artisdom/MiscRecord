#include <QCoreApplication>
#include <QCryptographicHash>
#include <QtConcurrent\QtConcurrent>

QByteArray getFileMd5(QString filePath)
{
	QFile localFile(filePath);
	if (!localFile.open(QFile::ReadOnly))
	{
		qDebug() << "file open error.";
		return 0;
	}
	quint64 totalBytes = localFile.size();
	quint64 bytesWritten = 0;
	quint64 bytesToWrite = totalBytes;
	quint64 loadSize = 1024 * 4;

	using Hash = QCryptographicHash;
	Hash md5Hash(Hash::Md5);
	QByteArray buffer;
	while (true)
	{
		if (bytesToWrite > 0)
		{
			buffer = localFile.read(qMin(bytesToWrite, loadSize));
			md5Hash.addData(buffer);
			bytesWritten += buffer.length();
			bytesToWrite -= buffer.length();
			buffer.resize(0);
		}
		else break;

		if (bytesWritten == totalBytes) break;
	}
	localFile.close();
	return md5Hash.result();
}

bool asyncGetFileMd5(QString const& file, std::function<void(QByteArray const& md5)> callback)
{
	if (!QFile::exists(file)) return false;
	using Watcher = QFutureWatcher<QByteArray>;
	QSharedPointer<Watcher> watcher(new Watcher());
	QObject::connect(watcher.data(), &Watcher::finished, [=]()
	{
		callback(watcher->result());
	});
	watcher->setFuture(QtConcurrent::run(getFileMd5, file));
	return true;
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	qDebug() << asyncGetFileMd5(argv[0], [&](QByteArray const& md5)
	{
		qDebug() << md5.toHex();
		app.quit();
	});
	app.exec();
}