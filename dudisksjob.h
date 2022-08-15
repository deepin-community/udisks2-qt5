/*
 * Copyright (C) 2020 UOS Technology Co., Ltd.
 *
 * Author:     zccrs <zhangjide@deepin.com>
 *
 * Maintainer: xushitong<xushitong@uniontech.com>
 *             max-lv<lvwujun@uniontech.com>
 *             zhangsheng<zhangsheng@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DUDISKSJOB_H
#define DUDISKSJOB_H

#include <QObject>

class DUDisksJobPrivate;
class DUDisksJob : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DUDisksJob)

    Q_PROPERTY(QString path READ path CONSTANT FINAL)
    Q_PROPERTY(QStringList objects READ objects CONSTANT FINAL)
    Q_PROPERTY(bool cancelable READ cancelable CONSTANT FINAL)
    Q_PROPERTY(bool progressValid READ progressValid CONSTANT FINAL)
    Q_PROPERTY(double progress READ progress NOTIFY progressChanged FINAL)
    Q_PROPERTY(QString operation READ operation CONSTANT FINAL)
    Q_PROPERTY(quint32 startedByUid READ startedByUid CONSTANT FINAL)
    Q_PROPERTY(quint64 bytes READ bytes CONSTANT FINAL)
    Q_PROPERTY(quint64 expectedEndTime READ expectedEndTime NOTIFY expectedEndTimeChanged FINAL)
    Q_PROPERTY(quint64 rate READ rate NOTIFY rateChanged FINAL)
    Q_PROPERTY(quint64 startTime READ startTime CONSTANT FINAL)

public:
    ~DUDisksJob();
    QString path() const;
    QStringList objects() const;
    bool cancelable() const;
    bool progressValid() const;
    double progress() const;
    QString operation() const;
    quint32 startedByUid() const;
    quint64 bytes() const;
    quint64 expectedEndTime() const;
    quint64 rate() const;
    quint64 startTime() const;

public Q_SLOTS:
    void cancel(const QVariantMap &options);

Q_SIGNALS:
    void completed(bool success, QString message);
    void progressChanged(double progress);
    void rateChanged(quint64 rate);
    void expectedEndTimeChanged(quint64 expectedEndTime);

private:
    QScopedPointer<DUDisksJobPrivate> d_ptr;

    explicit DUDisksJob(QString path, QObject *parent = nullptr);

private Q_SLOTS:
    void onPropertiesChanged(const QString &interface, const QVariantMap &changed_properties);

    friend class DDiskManager;
};
#endif
